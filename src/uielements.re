module ActivityTable = {
  let component = ReasonReact.statelessComponent("ActivityTable");
  let make = (~rows, _children) => {
    ...component,
    render: _self => 
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
      {rows}
      </tbody>
          </table>
        </div>
      </div>
    </div>
  };
}


module ActivityRow = {
  let component = ReasonReact.statelessComponent("ActivityRow");
  let make = (~activity: Activities.t, _children) => {
    ...component,
    render: _self => 
        <tr>
        /* To Do: Add function that masks abbrev is same name */
          <td>(Utils.str("Working"))</td>
          <td> (Utils.str(activity.activity_name)) </td>
          <td>
            <a href=activity.program_homepage>
              {(Utils.str((activity.program_name) 
                ++ " ("
                ++ activity.program_short_name
                ++ ")"
                ))}
            </a>
          </td>
        </tr>
  };
};