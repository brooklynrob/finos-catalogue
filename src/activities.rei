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


