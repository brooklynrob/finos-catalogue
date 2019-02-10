/* let parseResponseJson = (~field, ~decoder) =>
  Json.Decode.field(field, Json.Decode.array(decoder), json); */

let list_to_set = l => List.fold_left(
  (a, e) => if (List.mem(e, a)) {a;} else { [e, ...a];}, [], l);

let str = ReasonReact.string;
  




 


