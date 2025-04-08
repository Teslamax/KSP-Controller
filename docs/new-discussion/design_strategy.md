# Design Strategy

## Physical Design

- Modules are kept compact and reusable (e.g., 1x4 key clusters)
- Front panel cut with tight-fitting cutouts for seamless device integration
- Mounting tabs for structural support with small support rings and standoffs

## Electrical

- I2C used for all key and encoder input boards (NeoKey, 4991)
- RGB used for context feedback (e.g., gear up/down, SAS, modes)
- Simpit telemetry data drives feedback (RGB, slider)

## Practical Considerations

- Panel and hole tolerances adjusted for powder coating (~0.1–0.2mm)
- Aluminum panel is main interface, Delrin or acrylic used as non-conductive backing
- Screw sizing focused around M3 or US #4 hardware (common at hardware stores)