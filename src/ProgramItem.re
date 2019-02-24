open Programs;

type program_item = {
  program: Programs.t,
  checked: bool
}

let component = ReasonReact.statelessComponent("ProgramItem");

let make = (~program, _children) => {
  ...component,
  render: _self => {
    <div>
      <input
        className="toggle"
        type_="checkbox"
      />
      <label>
        (Utils.str(program.program_name))
      </label>
    </div>
  }
};