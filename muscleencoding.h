#ifndef MUSCLEENCODING_H
#define MUSCLEENCODING_H

class QStringList;

class MuscleEncoding {
public:
    enum muscles {
        Front_Deltoids = 1 << 0,
        Side_Deltoids = 1 << 1,
        Rear_Deltoids = 1 << 2,
        Upper_Chest = 1 << 3,
        Middle_Chest = 1 << 4,
        Lower_Chest = 1 << 5,
        Upper_Traps = 1 << 6,
        Upper_Back = 1 << 7,
        Lower_Back = 1 << 8,
        Biceps = 1 << 9,
        Triceps = 1 << 10,
        Forearms = 1 << 11,
        Upper_Abs = 1<< 12,
        Lower_Abs = 1 << 13,
        Obliques = 1 << 14,
        Glutes = 1 << 15,
        Quads = 1 << 16,
        Calves = 1 << 17,
        Hamstrings = 1 << 18,
        Hip_Abductor = 1 << 19,
        Hip_Adductor = 1 << 20,

        Deltoids = Front_Deltoids | Side_Deltoids | Rear_Deltoids,
        Chest = Upper_Chest | Middle_Chest | Lower_Chest,
        Abs = Upper_Abs | Lower_Abs | Obliques,
        Hips = Hip_Abductor | Hip_Adductor


        // If we see front, side and rear, just spit out deltoids

    };
    // Takes in a QStringList and returns an int that has the encoding of the muscle groups
    static int encodeMuscleGroup(const QStringList &muscleGroups);
    // Takes in an int and returns a QStringList of muscles worked
    static QStringList decodeMuscleGroup(int coding);
};

#endif // MUSCLEENCODING_H
