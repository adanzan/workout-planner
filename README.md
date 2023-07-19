# Workout Planner

A GUI workout planner that has an interactive muscle anatomy diagram. 
> Built using: C++, Qt
***

## Components

### Interactive Muscle Anatomy Diagram  
> A map of the body with a selection element for each muscle group.  
<img width="526" alt="Muscle diagrams of the human body" src="https://github.com/adanzan/workout-planner/assets/72373198/7b751705-1e9d-4139-81f0-0471da9c5bba">
<br><br>

- When a muscle is selected, it is highlighted and the exercises in the left column are filtered to include only those that target the muscle.  
<img width="1379" alt="Quadriceps are highlighted on the diagram. Exercises that work the quadriceps are on the left." src="https://github.com/adanzan/workout-planner/assets/72373198/8e63a03a-2c30-4e95-88f1-f3fe7bfb0c60">
<br><br>

- When an exercise is clicked, the diagram highlights both the primary and secondary muscle groups targeted by the exercise.
<img width="1529" alt="Squat is selected. On the diagram, the glutes are highlighted in red while the quads and hamstrings are highlighted in yellow." src="https://github.com/adanzan/workout-planner/assets/72373198/e5cfdeeb-af03-4251-9c8b-9f5c362bea7a">
<br><br>

- Multiple muscle groups can be selected at the same time, by shift-clicking on subsequent muscle groups. 
<img width="1379" alt="Chest, quads, and calves are selected. The list has exercises that target the muscles." src="https://github.com/adanzan/workout-planner/assets/72373198/66f5fcee-350a-467c-b768-ce72916fcaa4">
<br><br><br>

### Exercise List 
> A column listing various exercises, with dropdown menus for each exercise listing the equipment needed.
<img width="393" alt="A list of exercises" src="https://github.com/adanzan/workout-planner/assets/72373198/74e2e477-b3e6-4631-b175-4f2b9c901f62">
<br><br>

- Under each exercise, there is a list of equipment combinations required to do the exercise. When selected, a picture is displayed.
<img width="544" alt="Combination of bench press & squat rack is selected. On the left, there are pictures of the two." src="https://github.com/adanzan/workout-planner/assets/72373198/ee07567c-4fbd-4e87-9f1f-d056c4cfdb03">

***
## Functions

#### Add and remove exercises to a plan.
***Add*** - Add exercises to a workout plan.
  > Hotkey: (return)

***Remove*** - Remove exercises from a workout plan.
  > Hotkey: (backspace)  
<img width="489" alt="Buttons for adding and removing" src="https://github.com/adanzan/workout-planner/assets/72373198/b111b4c1-00c3-40c0-b02d-7adfe8d9d27f">

#### Analyze workout routine
***Analyze*** - Highlights the muscle groups that are targeted and the magnitude they are worked by the current program.  
<br>
<img width="897" alt="Analyze button. On the diagram, various muscles are colored differently." src="https://github.com/adanzan/workout-planner/assets/72373198/f3ab9ad5-a459-4de8-ab2c-9e5736843664">

#### Print workout routine
***Print*** - Opens the print overlay and generates a document.
- The document includes:
    - The exercises in the *exercise list*  
    - Blank columns for sets and reps, for the user to input the desired number.  

## Authors

[adanzan](https://github.com/adanzan)  
[fswenton](https://github.com/fswenton)  
[wbogatyrenko](https://github.com/wbogatyrenko)  

## Acknowledgements

- Originally developed as a final project for CSCI0309 - OOP & GUI at Middlebury College.  
- Cloned from the original repository on 05/25/2023.
