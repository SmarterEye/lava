

#include "rtcore.h"

#include "../../no_rt_util.h"
#include "../../tbl.hpp"
#include "../LavaFlow.hpp"
#include "../shared/vec.hpp"

enum Slots
{
  // This is an example enumeration that is meant to be helpful, though is not strictly neccesary. Referencing slots by a name will generally be less error prone than using their index and remembering what each index is for
  SLOT_IN          = 0,        
  BOUNDING_BOX_OUT = 0
};

struct Triangle { int v0, v1, v2; };

RTCDevice g_device = nullptr;
RTCScene   g_scene = nullptr;
RTCBounds    g_bnd;

tbl bndToIdxVerts(LavaParams const* lp, RTCBounds const& b)
{
  using namespace std;
    
  tbl  px = LavaMakeTbl(lp);
  tbl  py = LavaMakeTbl(lp);
  tbl  pz = LavaMakeTbl(lp);
  tbl  iv = LavaMakeTbl(lp);

  px.setArrayType<f32>();
  py.setArrayType<f32>();
  pz.setArrayType<f32>();

  px.push(b.lower_x);
  px.push(b.upper_x);
  px.push(b.upper_x);
  px.push(b.lower_x);
  px.push(b.lower_x); //
  px.push(b.upper_x);
  px.push(b.upper_x);
  px.push(b.lower_x);

  py.push(b.lower_y);
  py.push(b.lower_y);
  py.push(b.upper_y);
  py.push(b.upper_y);
  py.push(b.lower_y); //
  py.push(b.lower_y);
  py.push(b.upper_y);
  py.push(b.upper_y);

  pz.push(b.lower_z);
  pz.push(b.lower_z);
  pz.push(b.lower_z);
  pz.push(b.lower_z);
  pz.push(b.upper_z); //
  pz.push(b.upper_z);
  pz.push(b.upper_z);
  pz.push(b.upper_z);

  tbl ind = LavaMakeTbl(lp);
  ind.setArrayType<u32>();

  ind.push( 0u ); 
  ind.push( 1u );
  ind.push( 1u );
  ind.push( 2u );
  ind.push( 2u );
  ind.push( 3u );
  ind.push( 3u );
  ind.push( 0u );

  ind.push( 0u ); 
  ind.push( 4u );
  ind.push( 1u );
  ind.push( 5u );
  ind.push( 2u );
  ind.push( 6u );
  ind.push( 3u );
  ind.push( 7u );

  ind.push( 4u ); 
  ind.push( 5u );
  ind.push( 5u );
  ind.push( 6u );
  ind.push( 6u );
  ind.push( 7u );
  ind.push( 7u );
  ind.push( 4u );

  TO(8,i){ 
    ind.push( (u32)i ); 
  };

  //px[0] = b.lower_x;
  //px[1] = b.upper_x;
  //px[2] = b.upper_x;
  //px[3] = b.lower_x;
  //
  //py[0] =  b.lower_y;
  //py[1] =  b.lower_y;
  //py[2] =  b.upper_y;
  //py[3] =  b.upper_y;
  //
  //TO(4,i){
  //  px[i]   = b.lower_x;
  //  px[i+4] = b.upper_x;
  //}
  //TO(4,i){
  //  py[i*2]  =  b.lower_y;
  //  py[i+4]  =  b.upper_y;
  //}

  iv("indices")     = &ind;
  iv("positions x") = &px;
  iv("positions y") = &py;
  iv("positions z") = &pz;
  iv("mode")        = 1;            // 0 should be points, 1 should be lines
  iv("type")        = tbl::StrToInt("IdxVerts");
  iv.flatten();

  return move(iv);
}

extern "C"          // Embree3 Scene Message Node
{
  const char* description = "Takes in geometry that will be sorted into an acceleration structure and ultimatly used to trace rays";                                     // description

  const char*  InTypes[]  = {"IdxVerts",               nullptr};          // This array contains the type that each slot of the same index will accept as input.
  const char*  InNames[]  = {"Input Scene Geometry",   nullptr};          // This array contains the names of each input slot as a string that can be used by the GUI.  It will show up as a label to each slot and be used when visualizing.
  const char* OutTypes[]  = {"IdxVerts",               nullptr};          // This array contains the types that are output in each slot of the same index
  const char* OutNames[]  = {"Scene Bounds",           nullptr};          // This array contains the names of each output slot as a string that can be used by the GUI.  It will show up as a label to each slot and be used when visualizing.

  void Tracer_construct()
  {
    g_bnd.lower_x = 0.f;
    g_bnd.lower_y = 0.f;
    g_bnd.lower_z = 0.f;
    g_bnd.upper_x = 1.f;
    g_bnd.upper_y = 1.f;
    g_bnd.upper_z = 1.f;

    /* create new Embree device */
    g_device = rtcNewDevice("");
    //error_handler(nullptr,rtcGetDeviceError(g_device));

    /* set error handler */
    //rtcSetDeviceErrorFunction(g_device,error_handler,nullptr);

    /* create scene */
    g_scene = rtcNewScene(g_device);

    /* add cube */
    //addCube(g_scene);

    /* add ground plane */
    //addGroundPlane(g_scene);

    /* commit changes to scene */
    //rtcCommitScene (g_scene);

    /* set start render mode */
    //renderTile = renderTileStandard;
    //key_pressed_handler = device_key_pressed_default;
  }
  void Tracer_destruct()
  {
    rtcReleaseScene(g_scene);
    rtcReleaseDevice(g_device);
  }

  uint64_t Tracer(LavaParams const* lp, LavaFrame const* in, lava_threadQ* out) noexcept
  {
    using namespace std;

    SECTION(input packet loop)
    {
      u32 i=0;
      while( LavaNxtPckt(in, &i) )
      {
        tbl idxVerts( (void*)(in->packets[i-1].val.value) );
    
        RTCGeometry mesh = rtcNewGeometry(g_device, RTC_GEOMETRY_TYPE_TRIANGLE);

        tbl      px = idxVerts("positions x");
        tbl      py = idxVerts("positions y");
        tbl      pz = idxVerts("positions z");
        u64 vertCnt = px.size();
        v4f*  verts = (v4f*)rtcSetNewGeometryBuffer(mesh,RTC_BUFFER_TYPE_VERTEX,0,RTC_FORMAT_FLOAT3,sizeof(v4f),vertCnt);

        TO(vertCnt,i){
          verts[i].x  =  px[i];
          verts[i].y  =  py[i];
          verts[i].z  =  pz[i];
          verts[i].a  =  1.f;
        }

        tbl     ind = idxVerts("indices");
        u64  triCnt = (u64)ind.size() / 3;
        Triangle* triangles = (Triangle*)rtcSetNewGeometryBuffer(mesh,RTC_BUFFER_TYPE_INDEX,0,RTC_FORMAT_UINT3, sizeof(Triangle), (int)triCnt);

        TO(triCnt,i){
          auto idx = i * 3;
          triangles[i].v0  =  ind[idx + 0];
          triangles[i].v1  =  ind[idx + 1];
          triangles[i].v2  =  ind[idx + 2];
        }
        
        rtcCommitGeometry(mesh);

        u32 geomID = rtcAttachGeometry(g_scene, mesh);
        rtcReleaseGeometry(mesh);
    
        rtcCommitScene(g_scene);

        rtcGetSceneBounds(g_scene, &g_bnd);
        tbl bndIV = bndToIdxVerts(lp, g_bnd);
        out->push( LavaTblToOut(move(bndIV),BOUNDING_BOX_OUT) );           // this demonstrates how to output a tbl into the first output slot
      }
    }

    return 1;
  }

  LavaNode LavaNodes[] =
  {
    {
      Tracer,                                      // function
      Tracer_construct,                            // constructor - this can be set to nullptr if not needed
      Tracer_destruct,                             // destructor  - this can also be set to nullptr 
      LavaNode::MSG,                               // node_type   - this should be eighther LavaNode::MSG (will be run even without input packets) or LavaNode::FLOW (will be run only when at least one packet is available for input)
      "Tracer",                                    // name
      InTypes,                                     // in_types    - this can be set to nullptr instead of pointing to a list that has the first item as nullptr 
      InNames,                                     // in_names    - this can be set to nullptr instead of pointing to a list that has the first item as nullptr 
      OutTypes,                                    // out_types   - this can be set to nullptr instead of pointing to a list that has the first item as nullptr 
      OutNames,                                    // out_names   - this can be set to nullptr instead of pointing to a list that has the first item as nullptr
      description,                                 // description
      0                                            // version 
    },                                             

    LavaNodeListEnd                                // This is a constant that has all the members of the LavaNode struct set to 0 or nullptr - it is used as a special value that ends the static list of LavaNodes. This negates the need for a separate static variable that gives the size of the list, which would be have to be kept in sync and therefore be error prone.
  };

  __declspec(dllexport) LavaNode* GetLavaNodes()
  {
    return (LavaNode*)LavaNodes;
  }
}






//Vertex* vertices = (Vertex*) rtcSetNewGeometryBuffer(mesh,RTC_BUFFER_TYPE_VERTEX,0,RTC_FORMAT_FLOAT3,sizeof(Vertex),8);
//int tri = 0;
//
// geometry attribute for vert colors
//rtcSetGeometryVertexAttributeCount(mesh,1);
//rtcSetSharedGeometryBuffer(mesh,RTC_BUFFER_TYPE_VERTEX_ATTRIBUTE,0,RTC_FORMAT_FLOAT3,vertex_colors,0,sizeof(Vec3fa),8);
//
//return geomID;
//
//for(auto& kv : inputTbl){  // this loop demonstrates how to iterate through non-empty map elements
//}	