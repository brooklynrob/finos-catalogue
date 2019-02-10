[%bs.raw {|require('./app.css')|}];

[@bs.module] external finos : string = "./finos.png";

let test_json = {
  Activities.program_name: "my programName",
  Activities.program_short_name: "program short",
  Activities.program_homepage: "programName",
  Activities.activity_name: "activity name"
}

type state = 
  | Loading
  | Error
  | Loaded(Activities.activities);

type action =
  | ActivitiesFetch
  | ActivitiesFetched(Activities.activities)
  | ActivitiesFailedToFetch;



let decodeActivity = json =>
  Json.Decode.{
    Activities.program_name: json |> field("programName", string),
    Activities.program_short_name: json |> field("programShortName", string),
    Activities.program_homepage: json |> field("programHomePage", string),
    Activities.activity_name: json |> field("activityName", string) 
  };

let parseActivitiesResponseJson = json =>
  Json.Decode.field("activities", Json.Decode.array(decodeActivity), json);

let fetchActivities = () =>
  Js.Promise.(
    Bs_fetch.fetch(Config.activities_json_url)
      |> then_(Bs_fetch.Response.text)
      |> then_(
        jsonText => {
          resolve(parseActivitiesResponseJson(Js.Json.parseExn(jsonText)))
        }
      )
  );

module ActivityItem = {
  let component = ReasonReact.statelessComponent("ActivityItem");
  let make = (~activity: Activities.t, _children) => {
    ...component,
    render: _self => 
        <tr>
          <td> (Utils.str(activity.program_name)) </td>
          <td> (Utils.str(activity.program_short_name)) </td>
          <td> (Utils.str(activity.program_homepage)) </td>
          <td> (Utils.str(activity.activity_name)) </td>
        </tr>
  };
};

let component = ReasonReact.reducerComponent("App");
let make = (_children) => {
  ...component,
  initialState: _state => Loading,
  reducer: (action, _state) =>
    switch (action) {
    | ActivitiesFetch => 
    ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.(
              fetchActivities()
              |> then_(activities =>
                  activities
                  |> (activities => self.send(ActivitiesFetched(activities)))
                  |> resolve
              )
              |> catch(_err =>
                   Js.Promise.resolve(self.send(ActivitiesFailedToFetch))
                 )
              |> ignore
            )
        ),
      )
    | ActivitiesFetched(activities) => ReasonReact.Update(Loaded(activities))
    | ActivitiesFailedToFetch => ReasonReact.Update(Error)
    },
  didMount: self => self.send(ActivitiesFetch),

  render: (self) => {
    let rows = switch self.state {
    | Loading => <div><tr span=2><td>(Utils.str("Loading..."))</td></tr></div>
    | Error => <div><tr span=2><td>(Utils.str("Sorry. Unable to load Activities"))</td></tr></div>
    | Loaded(activities) => 
        Js.log("The list of programs is:")
        Js.log(Programs.create_program_list(activities)); 
        ReasonReact.array(
        Array.map(
          (activity: Activities.t) => <ActivityItem activity=activity />,
          activities
        )
      )
    };  

    <div className="container">
      <div className="row">
        <div className="col s12 board">
          <table id="simple-board" className="table table-striped table-sm">
          <tbody><tr>
              <th>(Utils.str("Program Name"))</th>
              <th>(Utils.str("Program Short Name"))</th>
              <th>(Utils.str("Program URL"))</th>
              <th>(Utils.str("Activity Name"))</th>
            </tr>
         
              {rows}
            </tbody>
          </table>
        </div>
      </div>
    </div>
  }
};
