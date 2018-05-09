# LAVA - Live Asynchronous Visual Architecture

LAVA is meant to simplify general purpose native software while allowing every piece to be lock free and asynchronous.

[![Load Obj](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Thumb_Demo_LoadObj.gif "")](#load-obj)
[![Camera Rays](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Thumb_Demo_CameraRays.gif "")](#camera-rays)
[![Brandisher Elements](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Thumb_Demo_BrandisherElements.gif "")](#brandisher-elements)
[![Trace](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Thumb_Demo_Trace.gif "")](#trace)
[![Interactive Trace](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Thumb_Demo_InteractiveTrace.gif "")](#interactive-trace)
[![Constant Bake](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Thumb_Demo_ConstantBake.gif "")](#constant-bake)
[![Shade Rays](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Thumb_Demo_ShadeRays.gif "")](#shade-rays)
[![Constant Shade](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Thumb_Demo_ConstantShade.gif "")](#constant-shade)

LAVA is designed to **_both_** significantly **_speed up development_** AND as a simple way to create **_signifcant amounts of lock free concurrency_**.  It is written in C++11 and meant to potentially work with any language that can compile a shared library that exposes standard function calls.  The building blocks are single file libraries with no dependencies other than the C++11 standard library. 

| __Tools__ | [![Fissure](images/THUMB_Fissure_5_8_2018.png "Fissure")](#fissure) | [![Visualizer](images/THUMB_craftsman_visualizer001.png "Visualizer")](#visualizer) | [![Brandisher](images/THUMB_craftsman_brandisher001.png "Brandisher")](#brandisher) |
| :---: | :---: | :---: | :---: |

| __Files__ | [Simdb.hpp](https://github.com/LiveAsynchronousVisualizedArchitecture/simdb) | [LavaFlow.hpp](Libraries.md#LavaFlow.hpp) | [tbl.hpp](Libraries.md#tbl.hpp) |
|  :---:    |          :---:         |         :---:                |       :---:        |

### Classic Software Problems
|[*Scalability*](#scal)     |[*Iterations*](#iter)  |[*Modularity*](#mod)    |[*Concurrency*](#concr)       |[*Debugging*](#debug)   |
|       :---:               |      :---:            |   :---:                |    :---:                     |   :---:                |
|[OpenGL Graph](#graphui)   |[Live Reloading](#live)|[Shared Libs](#libs)    |[Execute in Parallel](#async) |[Shared Memory](#shrmem)|
|[Clear Interfaces](#clear) |[Output Baking](#bake) |[Crash Isolation](#crsh)|[Lock Free](#lkfree)          |[Visualization](#viz)   |
|[Flow+Msg Nodes](#flow-msg)|[Visualization](#viz)  |[Serial Data](#serial)  |[Persistant Threads](#thrds)  |[Tbl and Stats](#stats) |

 - <a id="scal"> __Scalable Complexity__ </a> - High level structure is not strictly enforced (or doesn't exist) and often subverted in some way to accomodate extra data/communication.
  
 - <a id="iter"> __Iterations__ </a> - As program size increases, iterations decrease due to re-compilation time, linking time, and the time to re-run the program when testing.
  
- <a id="mod"> __Modularity__ </a> - Modularity often breaks down due to data dependencies at run time and source dependencies at compile time, making re-use more difficult and increasing the barrier to entry for anyone to a project.

- <a id="concr"> __Concurrency__ </a> - Many techniques and libraries exist, often as heavy dependencies that have narrow use cases where they excel. Concurrency, parallelism and asynchronous design are perpetually difficult to get right and fragmented in their use.

- <a id="debug"> __Debugging__ </a> - Often means using slow builds, multiple runs to narrow down the problem and examining the state individual variables line by line.

### How LAVA Confronts These Problems

#### High Level Structure
- <a id="graphui"> __Graph UI__ </a> - A fluid, openGL accelerated UI for architecting software visually while implementing incrementally.

- <a id="clear"> __Clear Inputs and Outputs__ </a> - Every node has inputs and outputs that show up visually making their scope clear.  Programs can be created from relativly few nodes. simplifying the comprehension of how large projects fit together and how their pieces interact. 

- <a id="flow-msg"> __Data Flow and Message Passing__ </a> - Flow nodes can be used for stateless transformations, making any data separated into a packet be dealt with concurrently.  Message nodes can hold state, use flow nodes and dictate the overall behavior of a program. 
  
#### Iterations, Interactivity and Testing 

- <a id="live">__Live Reloading__</a> -  - Input data can be frozen and a single node can be recompiled, automatically hot reloaded, then automatically run using the now static input.  This enables fast iteration even in a large program by isolating a single piece and its input while continuously viewing its output.

- <a id="bake">__Constant Nodes__</a> - Constant nodes can offer a way to change input in real time for interactive testing with visualization of results.

- <a id="viz">__Visualization__</a> - Visualizations happen with lock free shared memory to external processes and does not interfere with the execution of the main program.

#### Modularity
- <a id="libs">__Shared Libraries__</a> - Contain one or more nodes and can change while the program is running. Compilation is isolated to the lib being revised as well as run time checks in debug builds.  

- <a id="crsh">__Interrupts and Exceptions__</a> - The LAVA loop catches low level interrupts so that a crash shows up in the graph as a red halo around the crashed node.

- <a id="serial">__Serialized Node IO__</a> - All communication between nodes is passed as pointer to a single span of contiguous memory. This means that all IO can be saved as a file, written to shared memory for visualization and debugging.  While this can work with any data structure that can be serialized, data structures that always use a single span of memory (like tbl.hpp) are likely to be a good default. 

#### Concurrency, Parallelism and Asynchronous Design

- <a id="async">__Separate Data Executes Concurrently__</a> - Every packet of data can be dealt with concurrently, giving a program lock free asynchronous execution with little effort. Parallelism is dictated by the amount that data can be isolated

- <a id="lkfree">__Lock Free by Default__</a> - Threads take packets from a queue and execute them using their destination node.  Memory for node IO is allocated lock free and owned by the thread using reference counting. Part of each thread's loop is deallocating memory after each node it executes. Even visualization is lock free using simdb.

- <a id="thrds">__Threads Persist and Loop__</a> - Threads are meant to be created initially and loop, finding packets and executing them with their destination node. Each thread's stack can be used as thread local  eliminates overhead such as global memory allocation (which can lock) of thread creation.

#### Debugging

- <a id="shrmem">__Shared Memory__</a> - The use of simdb allows extremlely fast IPC (interprocess communication) over shared memory.  Visualizing data (with the [Visualizer](#visualizer) tool) or examining data (with the [Brandisher](#brandisher) tool) while a program is running is easy and has minimal performance over head due to a lock free design and thread local output.  

- <a id="stats">__Tbl Tree View With Statistics__</a> - [Brandisher](#brandisher) displays any tbl in shared memory, even if it can't be visualized. Tbls and their sub-tbls are shown as trees. Arrays are shown using a graph along with statistics such as mean, median and mode. Keys are show with their types and values.

### Tools

<a id="fissure"></a> <a id="visualizer"></a>

|    Fissure                      |   Visualizer       |
|     :---:                       |     :---:          |
| ![Fissure](images/Fissure_5_8_2018.png) | ![Visualizer](images/craftsman_visualizer001.jpg) |
| Fissure is the node graph UI.  It can be used to construct a graph of nodes, run the program, visualize outputs, see node errors and view timing information about the nodes. | [Tables](README.md#tblhpp) that are in the IdxVerts format (3D geometry with optional normals, vertex colors, uvs, and a color texture map)  will be picked up by the visualizer and displayed with openGL. |

|<a id="brandisher">__Brandisher__</a>|          |
|          :---:                      |  :---    |
|![Brandisher](images/craftsman_brandisher001.png)|<br>The brandisher is a tool for viewing tables and their sub-tables in shared memory. It can display a graph of the arrays' values as well as their basic statistics. <br><br>While some of the points making up the craftsman model are less than 0 on the Y axis, most are above 0.  <br><br>We also see minimum, maximum, average (mean), most common (mode), and median (middle) values as well as the variance. <br><br>This is a useful way to get a high level view on arrays containing too many values to be looked at directly as text.<br>|

### Examples

<a id="load-obj"> A constant file path is passed to an obj file loader node. </a>
The LoadObj node shown here is basically a wrapper around the [Tiny Obj Loader](https://github.com/syoyo/tinyobjloader) by [Syoyo Fujita](https://github.com/syoyo)
![alt text](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Demo_LoadObj.gif "A constant file path is passed to an obj file loader node.")

<br>

<a id="camera-rays">Ray tracing rays generated and visualized in real time as a memory mapped tbl file (the purple constant node) is changed. </a>
![alt text](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Demo_CameraRays.gif "Ray tracing rays generated and visualized in real time as a memory mapped tbl file (the purple constant node) is changed.")

<br>

<a id="brandisher-elements">Here the same tbl is show in two different places. On the right being edited as part of a const node (which just reads a .const file from disk). On the left it is read from shared memory.</a>
![Brandisher Elements](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Demo_BrandisherElements.gif "Here the same tbl is show in two different places. On the right being edited as part of a const node (which just reads a .const file from disk). On the left it is read from shared memory.")

<br>

<a id="trace">A trace node (a wrapper around [the Embree ray tracing library from Intel](https://github.com/embree/embree)) is added and generated rays are traced to find where they collide with geometry.</a>
![Trace](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Demo_Trace.gif "A trace node (a wrapper around the Embree ray tracing library from Intel) is added and generated rays are traced to find where they collide with geometry.")

<br>

<a id="interactive-trace">The field of view for the generated rays is changed and visualized outputs are updated in real time.</a>
![Interactive Trace](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Demo_InteractiveTrace.gif "The field of view for the generated rays is changed and visualized outputs are updated in real time.")

<br>

<a id="constant-bake">An output that is already in shared memory (blue highlight, then stepped once) is middle-click dragged to make a constant node. This cuts the dependency on the rest of the graph while writing out the result to a file on disc.</a>
![Constant Bake](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Demo_ConstantBake.gif "")

<br>

<a id="shade-rays">The traced rays are combined with the GGX BRDF to get new ray directions that originate from the model.  Their length when visualized is the result of their PDF (sample weight). </a>
![Shade Rays](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Demo_ShadeRays.gif "The traced rays are combined with the GGX BRDF to get new ray directions that originate from the model.  Their length when visualized is the result of their PDF (sample weight).")

<br>

<a id="constant-shade">The results of geometry loading, ray generation and ray tracing are written to a constant file for rapid iteration with no dependencies.</a>
![Constant Shade](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/Demo_ConstantShade.gif "The results of geometry loading, ray generation and ray tracing are written to a constant file for rapid iteration with no dependencies.")

<br>

<a id="shade-ray-hits"> Rays generated from a camera and traced to find their collisions with a 3D model using the embree library. </a>
![alt text](https://github.com/LiveAsynchronousVisualizedArchitecture/lava/blob/master/images/rays_shadeRayHits001.jpg "Rays generated from a camera and traced to find their collisions with a 3D model using the embree library.")


This is an example of rays generated from a camera and traced to find their collisions with a 3D model using the embree library.
  - An .obj model is loaded 
  - The model is passed to a message node that uses [the Embree ray tracing library from Intel](https://github.com/embree/embree) to sort the geometry into a BVH (bounding volume heirarchy acceleration structure for ray tracing)
  - The camera node generates rays and passes them to the scene node to be traced
  - The message node traces the rays and outputs both the traced rays colliding with geometry and a visualization of the traced rays 
  - A final node takes the traced rays and computes the outgoing ray from the ray hit point and normal
  
  
  ### F.A.Q (Frequently Anticipated Questions)
  
  ### Internals
  
  
