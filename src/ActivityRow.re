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
