type t = 
  {
    program_name: string, 
    program_short_name: string,
    program_homepage: string,
    activity_name: string,
  };

type activities = array(t);

let decodeActivity = json =>
  Json.Decode.{
    program_name: json |> field("programName", string),
    program_short_name: json |> field("programShortName", string),
    program_homepage: json |> field("programHomePage", string),
    activity_name: json |> field("activityName", string) 
  };

let fetchActivities = () =>
  Js.Promise.(
    Bs_fetch.fetch(Config.activities_json_url)
      |> then_(Bs_fetch.Response.text)
      |> then_(
        jsonText => {
          resolve(Parsers.parseResponseJson(
            ~field="activities", 
            ~json=Js.Json.parseExn(jsonText), 
            ~decoder=decodeActivity))
        }
      )
  );

