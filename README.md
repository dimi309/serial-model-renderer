Used for testing file parsing and rendering for robustness, this program will 
serially load and render 3D models from the resources/models folder, rotating 
them on the screen.

Before building, run the appropriate small3d dependencies preparation script
from small3d/deps/scripts.

Then from the main repository execute:

	mkdir build
	cd build
	# add -G"Visual Studio 17 2022" or -G"MinGW Makefiles" below
    # if building on Windows
	cmake .. -DCMAKE_CXX_STANDARD=17 
	cmake --build . # add --config Debug or --config Release if 
	                # building on Windows
					
Note: This is an integrated build with small3d, so including header files
      from the library in the serial model renderer source code is done with
	  double quotes and without the small3d/ directory prefix, for 
	  example `include "Renderer.hpp"` and not 
	  `include <small3d/Renderer.hpp>`.

![screenshot](screenshot.png)
