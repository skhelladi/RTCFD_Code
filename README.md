# Real-time Computational Fluid Dynamics

This repository presents a real-time CFD solver based on a "rough" representation of conservation equations. The solver is implemented in C/C++ for real-time purpose and Qt for the user interface and graphical renderings. It supports a wide range of features:
- 2D problems (3D in progress)
- real-time flow patern variation
- variety of obstacles (in progress)
- drag-and-drop obstacles
- postprocessing using: scalars (pressure, velocity, tracer), streamlines and velocity vectors

## Tutorial

<video width="800" height="400" controls>
  <source src="https://raw.githubusercontent.com/skhelladi/RTCFD_Code/master/doc/turorial_v0.01beta.mp4?token=GHSAT0AAAAAAB4LBJC4SSSK33OHP2REGCG6Y47D2PA" type="video/mp4">
</video>

## License
This project is licensed under the GPL-3 license.

Unless you explicitly state otherwise, any contribution intentionally submitted by you for inclusion in this project shall be licensed as above, without any additional terms or conditions.

## Authors
- Sofiane KHELLADI


### Code inspiration
This code is based on the theoretical developments and javascript code presented by Matthias Müller in "Ten Minute Physics" channel.

Link: https://matthias-research.github.io/pages/tenMinutePhysics/17-fluidSim.pdf
