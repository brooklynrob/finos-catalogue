open Programs;


let component = ReasonReact.statelessComponent("ProgramItem");

let make = (~program, ~onToggle, _children) => {
  ...component,
  render: _self => {
    /* Js.log("Checked is ...");
    Js.log(program.checked);
    Js.log("program is ...");
    Js.log(program); */
    <li className = "nav-item">
      <input
        className="toggle"
        type_="checkbox"
        checked=program.checked
        onChange=(program => onToggle(program))
      />
      <label>
        (Utils.str(program.program_short_name))
      </label>
    </li>
  }
};