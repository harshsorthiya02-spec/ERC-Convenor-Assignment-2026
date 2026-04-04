
# Pick-and-Place Robotic Arm Simulation (Simscape Multibody)

## Project Overview

This project implements a pick-and-place robotic arm using Simscape Multibody in MATLAB. The system consists of a gripper mounted on a rotating post, an incoming conveyor belt (Belt In), an outgoing conveyor belt (Belt Out), and a box. The objective was to make the robot pick the box from the incoming belt and place it onto the outgoing belt through a fully functional 3D simulation.

---

##  Initial Condition of the Model

The provided Simscape model was incomplete and non-functional. The following issues were observed:

* All major subsystems (Gripper, Belt In, Belt Out, Box, Commands) were present but **not connected**
* **World Frame block was missing**
* Required **Rigid Transform blocks were not present**
* **Belt Out subsystem had incomplete internal connections**
* Gripper subsystem had **unconnected prismatic and revolute joints**
* Signal routing for commands was incomplete (missing proper use of Goto/From)
* Simulation failed to run due to multiple connection and configuration errors

---

## Steps Taken to Fix the Model

### 1. Adding Required Blocks

* Added **World Frame** block to define the global reference frame
* Added two **Rigid Transform blocks**:

  * Transform Belt In → configured with −90° rotation about Z-axis
  * Transform Belt Out → configured with 180° rotation about Z-axis
* Added **Goto blocks** to route signals (tags: "In" and "Out")

---

### 2. Connecting the Top-Level Model

* Connected all physical subsystems (Gripper, Belt In, Belt Out, Box) to the **World Frame** through appropriate transforms
* Ensured proper frame chaining so that all bodies exist in a consistent coordinate system
* Connected force blocks (Box to Belt interactions) to both the box and respective belts

---

### 3. Fixing the Gripper Subsystem

* Connected **prismatic joints** to enable linear motion of the gripper fingers
* Ensured both fingers move symmetrically using a **Gain block of −1** for opposite motion
* Connected the **rod and post** correctly to transfer motion
* Linked gripper angle and position inputs from command signals

---

### 4. Fixing the Belt Subsystems

* Used **Belt In as reference** to fix Belt Out
* Completed missing connection in Belt Out between:

  * Gain → Integrator → Revolute joints (rollers)
* Ensured all rollers rotate consistently based on input speed signal

---

### 5. Signal Routing

* Properly connected command signals for:

  * Belt speeds
  * Gripper opening/closing
  * Post rotation
* Used **Goto and From blocks** to avoid clutter and ensure correct signal flow

---

##  Key Concepts Used

* **Prismatic Joints** → used for linear motion of gripper fingers
* **Revolute Joints** → used for rotation of rollers and arm
* **Rigid Transform** → used to position and orient components in 3D space
* **World Frame** → serves as the global reference for all bodies
* **Contact Forces** → used to simulate interaction between the box and conveyor belts

---

##  Errors Encountered and Debugging

* Initial simulation errors due to missing connections between blocks
* Incorrect orientation of belts caused unrealistic motion (box not moving or flying off)
* Missing transforms led to misaligned frames
* Fixed by:

  * Carefully comparing Belt Out with Belt In
  * Adjusting rotation angles in Rigid Transform blocks
  * Ensuring all physical components were connected to the World Frame

---

##  Final Result

The simulation runs successfully in 3D. The box moves along the incoming conveyor belt, is gripped by the robotic arm, lifted and transported, and then placed onto the outgoing conveyor belt. The motion is smooth and matches the expected pick-and-place behavior.

---
