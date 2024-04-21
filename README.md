# Flocking Behavior Simulation

Developed with Unreal Engine 5.2.1

Link to the video: https://youtu.be/6uR-edWA9Yw

## Overview
This simulation consists of agents ("boids") that navigate the empty 3D space following three rules of the Boids algorithm and a "Goal Setting" Tweak.

- Rule 1: Boids try to fly towards the centre of mass of neighbouring boids.

- Rule 2: Boids try to keep a small distance away from other objects (including other boids).

- Rule 3: Boids try to match velocity with near boids.


- Tweak: Goal Setting
  - A wind simulation vector that is added to the velocity of each boid, creating a uniform force. Additionally, I created a specific location where agents move along the x-axis in this region due to the wind effect, guiding the flock toward a designated target.

## Behavior in the game
In the game, agents start by quickly repulsing from each other due to rule 2, then settle into a formation due to rule 1 and constantly move due to rule 3. An external "wind" force causes a constant drift (left and right) along the X-axis, and the goal-seeking behavior directs the flock towards a specified point, which can be observed as a gradual movement in a common direction.
