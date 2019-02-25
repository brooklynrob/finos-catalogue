open Programs;

type state = list(Programs.t);

type action = 
  | Toggle_program(Programs.t)

let component = ReasonReact.reducerComponent("Filter");

let make = (~programs, ~activities, _children) => {
  ...component, /* spread the template's other defaults into here  */
  reducer: (action,_state) =>
    switch (action) {
    | Toggle_program(program) =>
      ReasonReact.Update(programs)
  },

  initialState: () => {
    programs
  },

  render: self => {
    <div>
      <div>
      (
        List.map(
          program =>
            <ProgramItem
              
              program
              onToggle=(_event => self.send(Toggle_program(program)))
              
            />,
          programs
        )
        |> Array.of_list
        |> ReasonReact.array
      )
      </div>
      <div>
        <ActivityTable
          activities=activities
          filtered_programs=Programs.filtered_programs_short_list_names(programs)
        />
      </div>
    </div>
  },
};