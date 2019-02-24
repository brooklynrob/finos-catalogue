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
let make = (~program_list_to_filter=?,_children) => {
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
          let all_programs_list = Programs.create_program_list(activities);
          let filtered_programs_list = 
            switch (program_list_to_filter) {
              | None => all_programs_list
              | Some(program_list_to_filter) => program_list_to_filter
            };
          <div>
            <div><Filter program_list=all_programs_list /></div>
            <div><ActivityTable
              activities=activities
              filtered_programs=Programs.programs_short_list_names(filtered_programs_list)
              />
            </div>
          </div>
    };
  }
};
