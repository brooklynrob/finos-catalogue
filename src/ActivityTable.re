open Activities;
  
let component = ReasonReact.statelessComponent("ActivityTable");

let make = (~activities=?, ~filtered_programs=?, ~msg="Could not load data", _children) => {
  ...component,
  render: _self => 
  switch (activities) {
    | None => <div>(Utils.str(msg))</div>
    | Some(activities) => {
      Js.log("filtered programs are:\n");
      Js.log(filtered_programs);
        let displayed_activities =
          switch (filtered_programs) {
          | None => activities
          | Some(filtered_programs) => 
              List.filter(
                activity => List.mem(activity.program_short_name, filtered_programs),
                Array.to_list(activities),
              ) 
              |> Array.of_list
          };
      <div className="container">
      <div className="row">
        <div className="col s12 board">
          <table id="simple-board" className="table table-striped table-sm">
          <tbody>
            <tr>
              <th>(Utils.str("Type"))</th>
              <th>(Utils.str("Name"))</th>
              <th>(Utils.str("Program"))</th>
        </tr>

        {ReasonReact.array(
          Array.map(
            (activity: Activities.t) => <ActivityRow 
              key=activity.activity_name
              activity=activity 
            />,
            displayed_activities
          )
        )}
        
        </tbody>
            </table>
          </div>
        </div>
      </div>
    }
  }
};