# Agentic Spline Tools (Unreal Engine Plugin)

Agentic Spline Tools is a lightweight Unreal Engine plugin that streamlines spline-driven motion for actors. It introduces a configurable `UAgenticSplineMoverComponent` and a small Blueprint library to quickly snap actors to splines or configure movers at runtime.

## Features

- Designer-friendly spline mover component with loop and ping-pong traversal.
- Independent forward and reverse traversal speeds.
- Optional rotation and scale alignment to spline data.
- Blueprint helpers for quickly snapping actors to spline distances and programmatically wiring up movers on any actor.
- Automatic spline discovery on BeginPlay when the owner already has a spline component attached.

## Folder Overview

```
Plugins/
└── AgenticSplineTools/
    ├── AgenticSplineTools.uplugin
    └── Source/
        └── AgenticSplineTools/
            ├── AgenticSplineTools.Build.cs
            ├── Public/
            │   ├── AgenticSplineLibrary.h
            │   └── AgenticSplineMoverComponent.h
            └── Private/
                ├── AgenticSplineLibrary.cpp
                ├── AgenticSplineMoverComponent.cpp
                └── AgenticSplineTools.cpp
```

## Installation

1. Copy the `Plugins/AgenticSplineTools` directory into your Unreal project root.
2. Regenerate project files (e.g., right-click the `.uproject` file and choose **Generate Visual Studio project files**).
3. Build the project. Unreal Editor will detect and compile the plugin during the next launch.

## Usage

1. Enable **Agentic Spline Tools** in your project's Plugin settings.
2. Add a `Spline Component` and an `Agentic Spline Mover Component` to any actor you want to animate along a spline.
3. Adjust movement properties (speed, looping, ping-pong, rotation/scale alignment) directly on the component.
4. Call `Start Movement`, `Stop Movement`, or `Set Normalized Time` from Blueprint or C++ to control playback.
5. Optional: Use the `Agentic Spline` Blueprint library nodes to snap actors to spline distances or configure movers at runtime.

## Requirements

- Unreal Engine 5.3 or newer (earlier versions may work but are untested).

## License

This plugin is released under the MIT License. Feel free to adapt or extend it for your projects.
