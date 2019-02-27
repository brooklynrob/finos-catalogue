open Programs;

type state = list(Programs.t);

type action = 
  | Toggle_program(Programs.t)

let component = ReasonReact.reducerComponent("Filter");

let make = (~programs, ~activities, _children) => {
  ...component, /* spread the template's other defaults into here  */
  reducer: (action,state) =>
    switch (action) {
    | Toggle_program(program_to_toggle) =>

      /* Js.log("program_to_toggle is:\n");
      Js.log(program_to_toggle); */

      let filtered_programs = List.map(
        program =>
          if (program.program_short_name == program_to_toggle.program_short_name,
              ) {
            {...program, checked: !program.checked};
          } else {
            program;
          },
        state,
      );
      /* Js.log("The filtered programs are:\n");
      Js.log(filtered_programs); */
      ReasonReact.Update(filtered_programs)
  },

  initialState: () => {
    programs
  },


  render: ({send,state}) => {
    <div>
      <nav className="navbar navbar-dark fixed-top bg-dark flex-md-nowrap p-0 shadow">
        <a className="navbar-brand col-sm-3 col-md-2 mr-0" href="#">(Utils.str("FINOS"))</a>
        
          <ul className="navbar-nav px-3">
          <li className="nav-item text-nowrap">
            <a className="nav-link" href="#">(Utils.str("Sign out"))</a>
          </li>
        </ul>
      </nav>

    <div className="container-fluid">
      <div className="row">
        <nav className="col-md-2 d-none d-md-block bg-light sidebar">
          <div className="sidebar-sticky">
            
            <ul className="nav flex-column">
              (
                List.map(
                  program =>
                    <ProgramItem
                      key=program.program_short_name
                      program
                      onToggle=(event => send(Toggle_program(program)))
                      
                    />,
                  state
                )
                |> Array.of_list
                |> ReasonReact.array
              )
              </ul>
            </div>
          </nav>

          <div className="chartjs-size-monitor">
            <ActivityTable
              activities=activities
              filtered_programs=Programs.filtered_programs_short_list_names(state)
            />
          </div>
        
        </div>
      </div>
    </div>
  },
};