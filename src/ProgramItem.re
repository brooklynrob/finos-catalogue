open Programs;


let component = ReasonReact.statelessComponent("ProgramItem");

let make = (~program, ~onToggle, _children) => {
  ...component,
  render: _self => {

    <div className = "view">
      <input
        className="toggle"
        type_="checkbox"
        checked=program.checked
        onChange=(_ => onToggle())
      />
      <label>
        (Utils.str("Program"))
      </label>
    </div>
  }
};