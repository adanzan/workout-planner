#ifndef MUSCLEENCODING_H
#define MUSCLEENCODING_H

class QStringList;

class MuscleEncoding {
public:
    enum muscles {
        Bit_Front_Deltoids = 0,
        Bit_Side_Deltoids,
        Bit_Rear_Deltoids,
        Bit_Upper_Chest,
        Bit_Middle_Chest,
        Bit_Lower_Chest,
        Bit_Upper_Traps,
        Bit_Upper_Back,
        Bit_Lower_Back,
        Bit_Biceps,
        Bit_Triceps,
        Bit_Forearms,
        Bit_Upper_Abs,
        Bit_Lower_Abs,
        Bit_Obliques,
        Bit_Glutes,
        Bit_Quads,
        Bit_Calves,
        Bit_Hamstrings,
        Bit_Hip_Abductor,
        Bit_Hip_Adductor,
        Bit_Neck,

        Front_Deltoids = 1 << Bit_Front_Deltoids,
        Side_Deltoids = 1 << Bit_Side_Deltoids,
        Rear_Deltoids = 1 << Bit_Rear_Deltoids,
        Upper_Chest = 1 << Bit_Upper_Chest,
        Middle_Chest = 1 << Bit_Middle_Chest,
        Lower_Chest = 1 << Bit_Lower_Chest,
        Upper_Traps = 1 << Bit_Upper_Traps,
        Upper_Back = 1 << Bit_Upper_Back,
        Lower_Back = 1 << Bit_Lower_Back,
        Biceps = 1 << Bit_Biceps,
        Triceps = 1 << Bit_Triceps,
        Forearms = 1 << Bit_Forearms,
        Upper_Abs = 1<< Bit_Upper_Abs,
        Lower_Abs = 1 << Bit_Lower_Abs,
        Obliques = 1 << Bit_Obliques,
        Glutes = 1 << Bit_Glutes,
        Quads = 1 << Bit_Quads,
        Calves = 1 << Bit_Calves,
        Hamstrings = 1 << Bit_Hamstrings,
        Hip_Abductor = 1 << Bit_Hip_Abductor,
        Hip_Adductor = 1 << Bit_Hip_Adductor,
        Neck = 1 << Bit_Neck,

        Deltoids = Front_Deltoids | Side_Deltoids | Rear_Deltoids,
        Chest = Upper_Chest | Middle_Chest | Lower_Chest,
        Abs = Upper_Abs | Lower_Abs | Obliques,
        Hips = Hip_Abductor | Hip_Adductor
    };
    // Takes in a QStringList and returns an int that has the encoding of the muscle groups
    static int encodeMuscleGroup(const QStringList &muscleGroups);
    // Takes in an int and returns a QStringList of muscles worked
    static QStringList decodeMuscleGroup(int coding);
};

#endif // MUSCLEENCODING_H
