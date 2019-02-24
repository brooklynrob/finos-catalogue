type t = 
  {
    program_name: string, 
    program_short_name: string,
    program_homepage: string,
  };

type programs = list(t);

let create_program_list = (activities:Activities.activities) : programs => {
  let array_of_programs = 
    Array.map(
      activity => {
        program_name: activity.Activities.program_name,
        program_short_name: activity.Activities.program_short_name,
        program_homepage: activity.Activities.program_homepage,
      },
      activities,
    );
  Js.log ("The array of programs is");
  Js.log (array_of_programs);
  Utils.list_to_set(Array.to_list(array_of_programs));
}; 

let programs_short_list_names = programs => {
  List.fold_left(
    (acc, program) => [program.program_short_name, ...acc],
    [],
    programs,
  )
};


