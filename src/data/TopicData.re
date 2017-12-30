type topics = {names: array(string)};

let topicsUrl = (repoName: string) =>
  "https://api.github.com/repos/billy-reilly/" ++ repoName ++ "/topics";

/* Accept header required as topics endpoint is in preview,
   see https://developer.github.com/v3/repos/#list-all-topics-for-a-repository */
let topicsHeaders =
  Bs_fetch.HeadersInit.make({
    "Accept": "application/vnd.github.mercy-preview+json"
  });

let parseTopics = (json: Js.Json.t) : topics => {
  names:
    json |> Json.Decode.field("names", Json.Decode.array(Json.Decode.string))
};

let fetchTopics = (repoName: string) =>
  Js.Promise.(
    Bs_fetch.fetchWithInit(
      topicsUrl(repoName),
      Fetch.RequestInit.make(~headers=topicsHeaders, ())
    )
    |> then_(Bs_fetch.Response.text)
    |> then_((jsonText) => resolve(parseTopics(Js.Json.parseExn(jsonText))))
  );
