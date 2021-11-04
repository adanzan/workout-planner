//TODO: Include Muscle Groups
    // For instance : Shoulders = 0 or 1 or 2
#include "muscle_encoding.h"

// The encoding for the muscles
muscle_encoding::muscle_encoding(){
    enum muscles {
        Front_Deltoids = 1 << 0,
        Side_Deltoids = 1 << 1,
        Rear_Deltiods = 1 << 2,
        Upper_Chest = 1 << 3,
        Middle_Chest = 1 << 4,
        Lower_Chest = 1 << 5,
        Traps = 1 << 6,
        Lats = 1 << 7,
        Upper_Back = 1 << 8,
        Lower_Back = 1 << 9,
        Biceps = 1 << 10,
        Triceps = 1 << 11,
        Forearm = 1 << 12,
        Upper_Abs = 1<< 13,
        Lower_Abs = 1 << 14,
        Obliqueus = 1 << 15,
        Glutes = 1 << 16,
        Quads = 1 << 18,
        Calves = 1 << 19,
        Hamstrings = 1 << 20,
        Hip_Abductor = 1 << 21,
        Hip_Adductor = 1 << 22
    };
}
