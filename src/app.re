[%bs.raw {|require('./app.css')|}];

[@bs.module] external finos : string = "./finos.png";

type state = 
  | Loading
  | Error
  | Loaded(Activities.activities);

type action =
  | ActivitiesFetch
  | ActivitiesFetched(Activities.activities)
  | ActivitiesFailedToFetch;

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
              Activities.fetchActivities()
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
    | Loading => <div>(Utils.str("Loading..."))</div>
    | Error => <div>(Utils.str("Sorry. Unable to load Activities"))</div>
    | Loaded(activities) => 
        Js.log("The list of programs is:")
        Js.log(Programs.create_program_list(activities)); 
        ReasonReact.array(
        Array.map(
          (activity: Activities.t) => <Uielements.ActivityRow activity=activity />,
          activities
        )
      )
    };  
      <Uielements.ActivityTable rows={rows} />  
  }
};
