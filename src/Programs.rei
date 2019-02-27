type t = 
  {
    program_name: string, 
    program_short_name: string,
    program_homepage: string,
    checked: bool
  };

let create_program_list : Activities.activities => list(t)

let filter_programs: list(t) => list(t);

let filtered_programs_short_list_names: list(t) => list(string);

