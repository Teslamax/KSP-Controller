// Mounting holes and components for 4980 + 2x 4991
/*
motorized linear potentiometer

147mm long x 17.5mm wide x 30mm depth

slide opening = 108mm x 2.8mm
slide = 1.2mm wide
mounting points from top = 120mm centered M3x0.5

*/
// === Constants ===
panel_thickness=1.6; // 3, 4.5, 5.6

powdercoat=0.1;

width4980 = 76.2;
height4980 = 21.59;
mount4980_x = 19.05;
mount4980_y = 8.25;

encoder_spacing = 25.4;
encoder_board_half = encoder_spacing / 2 + 13;
encoder_hole_offset = 10.15;
encoder_z_offset = -1.5; // board thickness

// === Modules ===

module NeoKey4980() {
    rotate([180, 0, 180])
        translate([-width4980/2, -height4980/2, 0])
            import("4980 NeoKey 1x4 QT/4980 NeoKey 1x4 QT.stl");
}

module rotary_encoder4991() {
    translate([0, 0, encoder_z_offset])
        rotate([0, 0, 90])
            import("4991 QT Rotary Encoder/4991 QT Rotary Encoder.stl");
}

module cutout_NeoKey4980(clearance = 0.5, radius = 2.5, stemmaSpace = 10) {
    bare_width=76.2;
    bare_height=21.59;
    width = bare_width + clearance;
    height = bare_height + clearance;
    color("yellow")
    linear_extrude(height = panel_thickness+2)
        union() {
            minkowski() {
                square([width - 2*radius, height - 2*radius], center = true);
                circle(r = radius, $fn = 32);
            }
                   // Notches for STEMMA QT connectors on each end
            translate([0, -3.2])
                square([bare_width+stemmaSpace*2, 10], center = true);
        }
}
module cutout_4991(clearance = 0.5, radius = 2.5, stemmaSpace = 10) {
    bare_size=25.4;
    size = bare_size + clearance;
    color("yellow")
    linear_extrude(height = panel_thickness+2)
    union() {
        minkowski() {
            square([size - 2*radius, size - 2*radius], center = true);
            circle(r = radius, $fn = 32);
        }
        // Notches for STEMMA QT connectors on each end
        square([bare_size+stemmaSpace*2, 10], center = true);
    }
}

// change radius to 1.5 when finished
module mounting_hole(pos, height = 10, radius = (1.25+powdercoat)) {
    translate([pos[0], pos[1], -5])
        color("red")
            cylinder(h = height, r = radius, $fn = 32);
}

encoder_holes = [
    [ encoder_hole_offset,  encoder_hole_offset],
    [-encoder_hole_offset,  encoder_hole_offset],
    [ encoder_hole_offset, -encoder_hole_offset],
    [-encoder_hole_offset, -encoder_hole_offset]
];

module place_encoder(pos) {
    // Place encoder STL
    translate([pos[0], pos[1], 0])
        rotary_encoder4991();
}
    
module place_encoder_cutout(pos) {
    // Place encoder STL
    translate([pos[0], pos[1], 0])
        cutout_4991(clearance = 0.5, radius = 2.5, stemmaSpace = 10); // panel cut-out
}

module place_encoder_holes(pos) {    
    // Place mounting holes
    for (pt = encoder_holes)
        mounting_hole([pt[0] + pos[0], pt[1] + pos[1]]);
}




module panel_outline(width = 120, height = 70, radius = 5, hole_r = (1.75+powdercoat), add_center = true) {
    difference() {
        // Base panel shape
        minkowski() {
            square([width - 2*radius, height - 2*radius], center = true);
            circle(r = radius, $fn = 48);
        }

        // Corner mounting holes
        union() {
            translate([ width/2 - 5,  height/2 - 5])
                circle(r = hole_r, $fn = 32);
            translate([-width/2 + 5,  height/2 - 5])
                circle(r = hole_r, $fn = 32);
            translate([ width/2 - 5, -height/2 + 5])
                circle(r = hole_r, $fn = 32);
            translate([-width/2 + 5, -height/2 + 5])
                circle(r = hole_r, $fn = 32);

            // Optional center hole
            if (add_center)
                translate([0, 2])
                    circle(r = hole_r, $fn = 32);
        }
    }
}

module mounting_tab(size = 7, radius = 2.0) {
        union()
        {
            circle(r = radius, $fn = 24);
            translate([(size/2),0,0])
                square([size,radius*2], center = true);
        }
    }

module place_encoder_tabs(pos, angles = [0, 0, 0, 0]) {
    for (i = [0 : len(encoder_holes)-1]) {
        pt = encoder_holes[i];
        angle = i < len(angles) ? angles[i] : 0;

        translate([pt[0] + pos[0], pt[1] + pos[1]])
            rotate([0, 0, angle])
                mounting_tab();
    }
}

// === Components ===

translate([0, 0, ((panel_thickness/2)+1.5)])
{
//    NeoKey4980();
    
//    place_encoder([-encoder_board_half, 30]);
//    place_encoder([ encoder_board_half, 30]);
}


// NeoKey 4980 mounting holes
/*
union() {
    mounting_hole([-mount4980_x,  mount4980_y]);
    mounting_hole([ mount4980_x,  mount4980_y]);
    mounting_hole([-mount4980_x, -mount4980_y]);
    mounting_hole([ mount4980_x, -mount4980_y]);
    
    place_encoder_holes([-encoder_board_half, 30]);
    place_encoder_holes([ encoder_board_half, 30]);
}
*/

/*
// backplate
projection(cut = true)
translate([0,16,0])
    linear_extrude(height = panel_thickness)
        panel_outline();
*/


// mounting plate
projection(cut = true)
color("lightblue")
    translate([0,0,-panel_thickness/2])
difference() {
    union() {
        difference() {
            translate([0,16,0])
                linear_extrude(height = panel_thickness)
                    panel_outline();
                
            // cutouts
            translate([0,0,0]) {
                cutout_NeoKey4980(clearance = 0.5, radius = 2.5, stemmaSpace = 10);
                place_encoder_cutout([-encoder_board_half, 30]);
                place_encoder_cutout([ encoder_board_half, 30]);
            }
        }
        linear_extrude(height = panel_thickness) {
            translate([mount4980_x,  mount4980_y,0]) rotate([0,0,90]) mounting_tab();
            translate([-mount4980_x,  mount4980_y,0]) rotate([0,0,90]) mounting_tab();
            translate([mount4980_x,  -mount4980_y,0]) rotate([0,0,-90]) mounting_tab();
            translate([-mount4980_x,  -mount4980_y,0]) rotate([0,0,-90]) mounting_tab();
            
            // Encoder 1 — top left, tabs angled toward center
            place_encoder_tabs([-encoder_board_half, 30],[45, 135, -45, -135]);  // angles for the four holes);

            // Encoder 2 — top right, tabs angled toward center
            place_encoder_tabs([encoder_board_half, 30],[45, 135, -45, -135]);
         }
    
    }
    union() {
    mounting_hole([-mount4980_x,  mount4980_y]);
    mounting_hole([ mount4980_x,  mount4980_y]);
    mounting_hole([-mount4980_x, -mount4980_y]);
    mounting_hole([ mount4980_x, -mount4980_y]);
    
    place_encoder_holes([-encoder_board_half, 30]);
    place_encoder_holes([ encoder_board_half, 30]);
}
}
