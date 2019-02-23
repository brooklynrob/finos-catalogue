type t = 
  {
    program_name: string, 
    program_short_name: string,
    program_homepage: string,
    activity_name: string,
  };

type activities = array(t);

let decodeActivity : Js.Json.t => t

let fetchActivities : unit => Js.Promise.t(array(t))

let filter_activities_by_program: (option(list(string)), list(t)) => list(t)


