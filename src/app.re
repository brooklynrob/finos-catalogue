[%bs.raw {|require('./app.css')|}];

[@bs.module] external finos : string = "./finos.png";

let str = ReasonReact.string;

type activity = {
  program_name: string, 
  program_short_name: string,
  program_homepage: string,
  activity_name: string,
};

type activities = array(activity);

let test_json = {
  program_name: "my programName",
  program_short_name: "program short",
  program_homepage: "programName",
  activity_name: "activity name"
}

type state = 
  | Loading
  | Error
  | Loaded(activities);

type action =
  | ActivitiesFetch
  | ActivitiesFetched(activities)
  | ActivitiesFailedToFetch;


let decodeActivity = json =>
  Json.Decode.{
    program_name: json |> field("programName", string),
    program_short_name: json |> field("programShortName", string),
    program_homepage: json |> field("programHomePage", string),
    activity_name: json |> field("activityName", string)
  };

let parseActivitiesResponseJson = json =>
  Json.Decode.field("activities", Json.Decode.array(decodeActivity), json);

let activities_json_url = "http://finos.github.io/activities.json";

let fetchActivities = () =>
  Js.Promise.(
    Bs_fetch.fetch(activities_json_url)
      |> then_(Bs_fetch.Response.text)
      |> then_(
        jsonText => {
          Js.log("In fetchActivities.\n. jsonText is...\n")
          Js.log(jsonText); 
          resolve(parseActivitiesResponseJson(Js.Json.parseExn(jsonText)))
        }
      )
  );


module ActivityItem = {
  let component = ReasonReact.statelessComponent("ActivityItem");
  let make = (~activity: activity, _children) => {
    ...component,
    render: _self =>
    <div className="activity">
    <h2> (ReasonReact.string("An Activity")) </h2>
      <label> (str(activity.program_name)) </label>
      <label> (str(activity.program_short_name)) </label>
    </div>
  };
};


let component = ReasonReact.reducerComponent("App");
let make = (_children) => {
  ...component,
  initialState: _state => Loading,
  reducer: (action, _state) =>
    switch (action) {
    | ActivitiesFetch => ReasonReact.Update(Loaded([|test_json|]))
    | ActivitiesFetched(activities) => ReasonReact.Update(Loaded(activities))
    | ActivitiesFailedToFetch => ReasonReact.Update(Error)
    },
  didMount: self => self.send(ActivitiesFetch),

  render: (self) => {
    switch self.state {
    | Loading => <div>(str("Loading..."))</div>
    | Error => <div>(str("Sorry. Unable to load Activities"))</div>
    | Loaded(activities) => 
        Js.log("In Loaded");
        Js.log(activities);
        ReasonReact.array(
        Array.map(
          (activity: activity) => <ActivityItem activity=activity />,
          activities
        )
      )
    };  
  }
};
