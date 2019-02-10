type t = 
  {
    program_name: string, 
    program_short_name: string,
    program_homepage: string,
  };

type programs = list(t);

let create_program_list : array(Activities.t) => programs;