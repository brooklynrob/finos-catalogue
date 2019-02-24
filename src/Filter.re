open Programs;

let component = ReasonReact.statelessComponent("Filter");

let make = (~program_list, _children) => {
  ...component, /* spread the template's other defaults into here  */
  render: _self => 
  <div> 
   {
    program_list
      |> List.map(program => Utils.str(program.program_short_name)) 
      |> Array.of_list
      |> ReasonReact.array
    }
  </div>
};