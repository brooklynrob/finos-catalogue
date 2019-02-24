open Programs;

let component = ReasonReact.statelessComponent("Filter");

let make = (~program_list, _children) => {
  ...component, /* spread the template's other defaults into here  */
  render: _self => {
    <div>
      (
        List.map(
          program =>
            <ProgramItem
              
              program
              
            />,
          program_list
        )
        |> Array.of_list
        |> ReasonReact.array
      )
    </div>;
  },
};