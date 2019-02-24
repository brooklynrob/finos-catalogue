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

  render: self => {
    switch self.state {
      | Loading => {<div><ActivityTable msg="Loading Data" /></div>}
      | Error => <div><ActivityTable msg="Error. Could not load data." /></div>
      | Loaded(activities) => 
          let program_list = Programs.create_program_list(activities);
          <div>
            <div><Filter program_list=program_list /></div>
            <div><ActivityTable activities=activities filtered_programs=["FDC3","FDX"]/></div>
          </div>
    };
  }
};
