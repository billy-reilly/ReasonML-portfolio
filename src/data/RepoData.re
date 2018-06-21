type repo = {
  name: string,
  html_url: string,
  updated_at: string,
  description: string,
  tags_url: string,
  fork: bool
};

let parseRepoJson = (json: Js.Json.t) : repo =>
  Json.Decode.{
    name: json |> field("name", string),
    html_url: json |> field("html_url", string),
    updated_at: json |> field("updated_at", string),
    description: json |> field("description", string),
    tags_url: json |> field("tags_url", string),
    fork: json |> field("fork", bool)
  };

let parseReposResponseJson = (json) =>
  json |> Json.Decode.array(parseRepoJson);

let reposUrl = "https://api.github.com/users/billy-reilly/repos";

let fetchRepos = () =>
  Js.Promise.(
    Bs_fetch.fetch(reposUrl)
    |> then_(Bs_fetch.Response.text)
    |> then_(
         (jsonText) =>
           resolve(parseReposResponseJson(Js.Json.parseExn(jsonText)))
       )
  );
