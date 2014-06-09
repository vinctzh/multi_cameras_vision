**Multi-cameras vision多目立体视觉**<br>
**Target:** Recover face 3D information from multi-cameras. Currently, 2 cameras are used.

**Process 2014-06-09**<br>
<li> Call multi-cameras and capture images at the same time.
<li> Rectify double-view images with cmamara parameters calibrated offline.
<li> Detect faces with my face detector;
<li> Detect seven feature points with codes from web.