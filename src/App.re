[%bs.raw {|require('./app.css')|}];

[@bs.module] external finos : string = "./finos.png";

type state = 
  | Loading
  | Error
  | Loaded(Activities.activities, list(Programs.t));

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
    | ActivitiesFetched(activities) => {
        /* start initial filter with all programs */
        let initial_programs_list = Programs.create_program_list(activities);
        ReasonReact.Update(Loaded(activities, initial_programs_list))
      }
    | ActivitiesFailedToFetch => ReasonReact.Update(Error)
    },
  didMount: self => self.send(ActivitiesFetch),

  render: self => {
    switch self.state {
      | Loading => {<div><ActivityTable msg="Loading Data" /></div>}
      | Error => <div><ActivityTable msg="Error. Could not load data." /></div>
      | Loaded(activities, programs) => 
          /* let filtered_programs_list = 
            switch (program_list_to_filter) {
              /* If program_list_to_filter is None, send all programs to table */
              | None => programs
              | Some(program_list_to_filter) => program_list_to_filter
            };
          */
          <div>
            <div>
              <Filter
                programs=programs
                activities=activities
              />
            </div>
          </div>
    };
  }
};
