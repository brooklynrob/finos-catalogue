type activity = {
  program_name: string;
  program_short_name: string;
  program_homepage: string;
  activity_name: string
};;

type activities = activity array;;

type activities_lst = activity list;;

type program = {
  program_name: string;
  program_short_name: string;
  program_homepage: string
};;

type programs = program list;;

let activity_array = [|
{program_name = "FDC3";
program_short_name = "FDC3";
program_homepage = "http://";
activity_name = "A workgroup test"
};
{program_name = "FO";
program_short_name = "FO";
program_homepage = "http://";
activity_name = "A workgroup test"
}
|];;

let list_to_set l = 
  List.fold_left (fun a e -> if List.mem e a then a else e :: a) [] l;;

let array_to_set arr =
Array.fold_left (fun a e -> if Array.mem e a then a else Array.append [|e|] a) [||] arr;;

let create_program_list (activities:activities) : programs =
  let array_of_programs =
    Array.map
      (fun activity  -> 
        { 
          program_name = (activity.program_name);
          program_short_name = (activity.program_short_name);
          program_homepage = (activity.program_homepage);
        })
    activities in
  list_to_set (Array.to_list array_of_programs);;


let filter_activites (programs:string list option) (activities:activity list) = function
| None -> activities
| Some programs-> [{program_name = "Program Name Test";
program_short_name = "Program Short";
program_homepage = "http://";
activity_name = "A workgroup test"
}];;

let filter_activites (programs:string list option) (activities:activity_lst) = function
| None -> activities
| Some programs-> List.filter (fun activity -> List.mem activity.program_short_name programs) activities;;


[{program_name = "Program Name Test";
program_short_name = "Program Short";
program_homepage = "http://";
activity_name = "A workgroup test"
}];;