type t = 
  {
    program_name: string, 
    program_short_name: string,
    program_homepage: string,
    checked: bool
  };

/* type programs = list(t); */

let create_program_list = (activities:Activities.activities) : list(t) => {
  let array_of_programs = 
    Array.map(
      activity => {
        program_name: activity.Activities.program_name,
        program_short_name: activity.Activities.program_short_name,
        program_homepage: activity.Activities.program_homepage,
        checked: true
      },
      activities,
    );
  /* Js.log ("The array of programs is");
  Js.log (array_of_programs); */
  Utils.list_to_set(Array.to_list(array_of_programs));
};

let filter_programs = programs => {
  List.filter (program => program.checked, programs)
}

let filtered_programs_short_list_names = programs => {
  let filtered_programs = filter_programs(programs);
  /* Js.log("filtered_programs in filtered_programs_short_list_names is \n");
  Js.log(filtered_programs); */
  List.fold_left(
    (acc, program) => [program.program_short_name, ...acc],
    [],
    filtered_programs,
  )
};


