type activity = {
  program_name: string;
  program_short_name: string;
  program_homepage: string;
  activity_name: string
};;

(* REASON 
type activity = {
  program_name: string,
  program_short_name: string,
  program_homepage: string,
  activity_name: string,
};
*)

type activities = activity array;;

type activities_lst = activity list;;


type program = {
  program_name: string;
  program_short_name: string;
  program_homepage: string;
  checked: bool;
};;

(* REASON 
type program = {
  program_name: string,
  program_short_name: string,
  program_homepage: string,
  checked: bool,
};
*)



type programs = program list;;

let activity_array = [|
{program_name = "FDC3";
program_short_name = "FDC3";
program_homepage = "http://";
activity_name = "A workgroup test"
};

(*
let activity_array = [|
{program_name : "FDC3",
program_short_name : "FDC3",
program_homepage : "http://",
activity_name : "A workgroup test"
}|];

*)

List.fold_left(fun acc program -> program.program_name::acc) [] program_lst;;

 [{program_name = "FDC3"; program_short_name = "FDC3";
    program_homepage = "https://"};
   {program_name = "FO"; program_short_name = "FO";
    program_homepage = "https://"}]



let programs = [
{program_name = "FDC3"; program_short_name = "FDC3"; program_homepage = "https://"; checked=true}, 
{program_name = "FO"; program_short_name = "FO"; program_homepage = "https://"; checked=false}
];;

let program_lst = [
{program_name = "FDC3"; program_short_name = "FDC3"; program_homepage = "https://"},
{program_name = "FO"; program_short_name = "FO"; program_homepage = "https://"},
{program_name = "Hadouken"; program_short_name = "Hadouken"; program_homepage = "https://"}
];;

let program_lst = [
{program_name : "FDC3", program_short_name : "FDC3", program_homepage : "https://"}, 
{program_name : "FO", program_short_name : "FO", program_homepage : "https://"}
];                                                          




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

let filter_activities (program_lst:string list option) (activities:activities_lst) = function
| None -> activities
| Some program_lst-> List.filter (fun activity -> List.mem activity.program_short_name program_lst) activities;;


let filter_activities_by_program =
  (prog_lst: option(list(string)), activities: list(activity)) =>
  switch (prog_lst) {
  | None => activities
  | Some(prog_lst) =>
    List.filter(
      activity => List.mem(activity.program_short_name, prog_lst),
      activities,
    ) 
  };




[{program_name = "Program Name Test";
program_short_name = "Program Short";
program_homepage = "http://";
activity_name = "A workgroup test"
}];;


List.filter (fun activity -> activity.program_short_name="FO") my_act_list;;

let my_act_list = (Array.to_list(activity_array));;
val my_act_list : activity list =
  [{program_name = "FDC3"; program_short_name = "FDC3";
    program_homepage = "http://"; activity_name = "A workgroup test"};
   {program_name = "FO"; program_short_name = "FO";
    program_homepage = "http://"; activity_name = "A workgroup test"}]


let program_lst = ["FDC3"];;
val program_lst : string list = ["FDC3"]
─( 15:48:56 )─< command 19 >───────────────────────────────────────────────────────────────────{ counter: 0 }─
utop # List.filter (fun activity -> List.mem activity.program_short_name program_lst) my_act_list;;
- : activity list =
[{program_name = "FDC3"; program_short_name = "FDC3";
  program_homepage = "http://"; activity_name = "A workgroup test"}]

List.filter (fun activity -> List.mem activity.program_short_name ["FO"; "Hadouken"]) my_act_list;;

let filter_activities (program_lst:string list option) (activities:activity list) = match program_lst with
| None -> activities
| Some program_lst-> List.filter (fun activity -> List.mem activity.program_short_name program_lst) activities;;

let filter_activities_by_program (prog_lst:string list option) (activities:activity list) =
match prog_lst with
| None -> activities
| Some prog_lst-> List.filter (fun activity -> List.mem activity.program_short_name prog_lst) activities;;



filter_activities (Some ["FO"; "Hadouken"]) my_act_list;;
- : activity list =
[{program_name = "FO"; program_short_name = "FO"; program_homepage = "http://";
  activity_name = "A workgroup test"}]



List.map(fun program -> 
  if (program.program_short_name = "FDC3") then
    {program with checked = not program.checked}
  else program
  ), programs;;


let fdc3_program = {program_name = "FDC3"; program_short_name = "FDC3";
     program_homepage = "https://"; checked = true};;

let fo_program = {program_name = "FO"; program_short_name = "FO";
     program_homepage = "https://"; checked = true};;

let hadouken_program = {program_name = "Hadouken"; program_short_name = "Hadouken";
     program_homepage = "https://"; checked = true};;

let programs =[fdc3_program;fo_program;hadouken_program];;

let flip_all programs = List.map(fun program ->
  {program with checked = not program.checked}) programs


let flip_programs program programs = List.map(fun program ->
  if String.equal program.program_short_name "FDC3" then {program with checked = not program.checked}
  else program
  ) programs;;

program.program_short_name == "FDC3" ? {
  ...program, program.checked: !(program.checked)} : program), programs;;



List.map
  (fun program -> if String.equal program.program_short_name "FDC3" then {program with checked = false} else program) programs;;


let toggle_program program programs = 
List.map
  (fun program -> if String.equal program.program_short_name "FDC3" then {program with checked = false} else program) programs;;

let toggle_program program_to_toggle programs = 
List.map
  (fun program -> if String.equal program.program_short_name program_to_toggle.program_short_name then {program with checked = not program.checked } else program) programs;;



type student = {
name : string;
classname: string
};;

let student1 = {name = "rob"; classname = "class1"};;

let student2 = {name = "toshi"; classname = "class2"};;

let students = [student1;student2];;

List.map
  (fun student -> if String.equal student.name "rob" then {student with name = "Taka"} else student) students;;



