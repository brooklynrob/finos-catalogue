module ActivityTable = {
  let component = ReasonReact.statelessComponent("ActivityTable");
  let make = (~rows, _children) => {
    ...component,
    render: _self => 
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
  };
}


module ActivityRow = {
  let component = ReasonReact.statelessComponent("ActivityRow");
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