**Multi-cameras vision**<br><br><br>
**Target:** Recover face 3D information from multi-cameras. Currently, 2 cameras are used.

<br>***Next functions***
<ul>
    <li> extract a bunch features points and find matches in both view images
    <li> calculate the 3D coordinates for good match pairs of feature points.
</ul>
<br>
**Process 2014-06-09:**<br>
<ul>
    <li> Call multi-cameras and capture images at the same time.
    <li> Rectify double-view images with cmamara parameters calibrated offline.
    <li> Detect faces with my face detector;
    <li> Detect seven feature points with codes from web.
</ul>

<br><br>
***Setting up with OpenCV 2.4.9 and working with Visual Studio 2010***

All rights reservers C Centvin Zhang http://www.centvin.com