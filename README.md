# enVR

enVR is a system designed to generate a 3D model from a sequence of 2D orthogonal projections of an object. These projections may either be read from a file or captured from a camera. The projections involve the front view, the two side planes, the back view and the top view. Once the images have been captured, enVR converts them into a 3D model drawn using OpenGL.

## Build Requirements

1. OpenCV: version 2.4 or higher
2. FreeGLUT: version 3.0.0
3. pkg-config
4. _Optional_ Hardware setup with 5 cameras attached equidistant from the object along the plans described above (Top, Front, Left, Back, Right).

## Installation

```
$ git clone https://gitlab.com/jerrytheo96/enVR.git
$ cd enVR
$ make
$ ./enVR
```

## License

enVR - System that constructs a 3D visual from a sequence of 2D images.\
Copyright (C) 2017  Abhijit J. Theophilus, Abhishek S. V.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

For the complete license, see LICENSE.md.

## Authors

Abhijit J. Theophilus (abhitheo96@gmail.com)\
Abhishek S. V. (abhishek.surbhat@gmail.com)
