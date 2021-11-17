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
        Traps = 1 << 6,
        Lats = 1 << 7,
        Upper_Back = 1 << 8,
        Lower_Back = 1 << 9,
        Biceps = 1 << 10,
        Triceps = 1 << 11,
        Forearms = 1 << 12,
        Upper_Abs = 1<< 13,
        Lower_Abs = 1 << 14,
        Obliques = 1 << 15,
        Glutes = 1 << 16,
        Quads = 1 << 18,
        Calves = 1 << 19,
        Hamstrings = 1 << 20,
        Hip_Abductor = 1 << 21,
        Hip_Adductor = 1 << 22,

        Deltoids = Front_Deltoids | Side_Deltoids | Rear_Deltoids,
        Chest = Upper_Chest | Middle_Chest | Lower_Chest,
        Abs = Upper_Abs | Lower_Abs | Obliques,
        Hips = Hip_Abductor | Hip_Adductor

        // If we see front, side and rear, just spit out deltoids

    };
    // Takes in a QStringList and returns an int that has the encoding of the muscle groups
    static int encodeMuscleGroup(const QStringList &muscleGroups);

    static QStringList decodeMuscleGroup(int coding);
};

#endif // MUSCLEENCODING_H
