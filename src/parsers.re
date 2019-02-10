let parseResponseJson = (~field, ~json, ~decoder) =>
  Json.Decode.field(field, Json.Decode.array(decoder), json);