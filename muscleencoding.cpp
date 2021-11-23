#include "muscleencoding.h"
#include <QStringList>

// Utility class, used to convert muscle encodings to strings and vice versa

// Converts a QStringList of Muscle Groups to encodings
int MuscleEncoding::encodeMuscleGroup(const QStringList &muscleGroups){
    // Initialises a 0 so that it could detect if nothing was detected
    int coding = 0;
    for (const QString &muscle : muscleGroups) {
        if (muscle == "Front Deltoids")
            coding |= Front_Deltoids;
        else if (muscle == "Side Deltoids")
            coding |= Side_Deltoids;
        else if (muscle == "Rear Deltoids")
            coding |= Rear_Deltoids;
        else if (muscle == "Upper Chest")
            coding |= Upper_Chest;
        else if (muscle == "Middle Chest")
            coding |= Middle_Chest;
        else if (muscle == "Lower Chest")
            coding |= Lower_Chest;
        else if (muscle == "Upper_Traps")
            coding |= Upper_Traps;
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
        else if (muscle == "Obliques")
            coding |= Obliques;
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
        else if (muscle == "Deltoids" || muscle == "Shoulders")
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
QStringList MuscleEncoding::decodeMuscleGroup(int coding){
    auto hasAll = [coding](int bits)->bool {
       return ((coding & bits) == bits);
    };
    auto hasSome = [coding](int bits)->bool {
       return (coding & bits);
    };

    QStringList muscles;

    if (hasAll(Upper_Traps)) muscles << "Upper Traps";
    if (hasAll(Upper_Back)) muscles << "Upper Back";
    if (hasAll(Lower_Back)) muscles << "Lower Back";

    if (hasAll(Biceps)) muscles << "Biceps";
    if (hasAll(Triceps)) muscles << "Triceps";
    if (hasAll(Forearms)) muscles << "Forearms";

    if (hasAll(Glutes)) muscles << "Glutes";
    if (hasAll(Quads)) muscles << "Quads";
    if (hasAll(Calves)) muscles << "Calves";
    if (hasAll(Hamstrings)) muscles << "Hamstrings";

    if (hasSome(Deltoids)) {
        if (hasAll(Deltoids)) muscles << "Deltoids";
        else {
            if (hasAll(Front_Deltoids)) muscles << "Front Deltoids";
            if (hasAll(Side_Deltoids)) muscles << "Side Deltoids";
            if (hasAll(Rear_Deltoids)) muscles << "Rear Deltoids";
        }
    }

    if (hasSome(Chest)) {
        if (hasAll(Chest)) muscles << "Chest";
        else {
            if (hasAll(Upper_Chest)) muscles << "Upper Chest";
            if (hasAll(Middle_Chest)) muscles << "Middle Chest";
            if (hasAll(Lower_Chest)) muscles << "Lower Chest";
        }
    }

    if (hasSome(Abs)) {
        if (hasAll(Abs)) muscles << "Abs";
        else {
            if (hasAll(Upper_Abs)) muscles << "Upper Abs";
            if (hasAll(Lower_Abs)) muscles << "Lower Abs";
            if (hasAll(Obliques)) muscles << "Obliques";
        }
    }

    if (hasSome(Hips)) {
        if (hasAll(Hips)) muscles << "Hips";
        else {
            if (hasAll(Hip_Abductor)) muscles << "Hip Abductor";
            if (hasAll(Hip_Adductor)) muscles << "Hip Adductor";
        }
    }

    return muscles;
}
