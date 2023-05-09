Used for testing file parsing and rendering for robustness, this program will 
serially load and render 3D models from the resources/models folder, rotating 
them on the screen.

Note: On some platforms where it is not provided by default, the C++ standard
needs to be set to 17, for example:

	cmake .. -DCMAKE_CXX_STANDARD=17

![screenshot](screenshot.png)
