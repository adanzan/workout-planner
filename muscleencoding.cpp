#include "muscleencoding.h"
#include <QStringList>

// Utility class, used to convert muscle encodings to

// Converts a QStringList of Muscle Groups to encodings
int MuscleEncoding::encodeMuscleGroup(const QStringList &muscleGroups){
    // Initialises a 0 so that it could detect if nothing was detected
    int coding = 0;
    for (QString muscle : muscleGroups) {
        if (muscle == "Front Deltoids")
            coding |= Front_Deltoids;
        else if (muscle == "Side Deltoids")
            coding |= Side_Deltoids;
        else if (muscle == "Rear Deltiods")
            coding |= Rear_Deltoids;
        else if (muscle == "Upper Chest")
            coding |= Upper_Chest;
        else if (muscle == "Middle Chest")
            coding |= Middle_Chest;
        else if (muscle == "Lower Chest")
            coding |= Lower_Chest;
        else if (muscle == "Traps")
            coding |= Traps;
        else if (muscle == "Lats")
            coding |= Lats;
        else if (muscle == "Upper Back")
            coding |= Upper_Back;
        else if (muscle == "Lower Back")
            coding |= Lower_Back;
        else if (muscle == "Biceps")
            coding |= Biceps;
        else if (muscle == "Triceps")
            coding |= Triceps;
        else if (muscle == "Forearms")
            coding |= Forearms;
        else if (muscle == "Upper Abs")
            coding |= Upper_Abs;
        else if (muscle == "Lower Abs")
            coding |= Lower_Abs;
        else if (muscle == "Obliqueus")
            coding |= Obliqueus;
        else if (muscle == "Glutes")
            coding |= Glutes;
        else if (muscle == "Quads")
            coding |= Quads;
        else if (muscle == "Calves")
            coding |= Calves;
        else if (muscle == "Hamstrings")
            coding |= Hamstrings;
        else if (muscle == "Hip Abductor")
            coding |= Hip_Abductor;
        else if (muscle == "Hip Adductor")
            coding |= Hip_Adductor;

        // Groups of muscles are bundled together
        else if (muscle == "Deltoids" || muscle == "Shoulder")
            coding |= Deltoids;
        else if (muscle == "Chest")
            coding |= Chest;
        else if (muscle == "Abs")
            coding |= Abs;
        else if (muscle == "Hips")
            coding |= Hips;
    }
    return coding;
}

// Converts muscle encodings to a QStringList of muscles
// TODO: Code the muscle encodings in
// Q: Figure out how to do the for loop
QStringList MuscleEncoding::decodeMuscleGroup(int coding){
    QStringList muscles;
    int code;
//    for (bool code : coding){
        //What do I do here?
        if ( code == Front_Deltoids){
            muscles << "Front Deltoids";
        }
//    }
    return muscles;
}
