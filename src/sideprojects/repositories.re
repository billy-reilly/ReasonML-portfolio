type state = {
  loadingRepos: bool,
  repos: option(array(RepoData.repo))
};

type action =
  | Loaded(array(RepoData.repo));

let component = ReasonReact.reducerComponent("Repositories");

/* Todo: find better way to access to moment... bs-moment? */
let sortRepos: array(RepoData.repo) => array(RepoData.repo) = [%bs.raw
  {|
    function(repos) {
      var moment = require('moment');
      return repos.filter(function(repo) {
        return !repo[5];
      }).sort(function(a, b) {
        return moment(a[2]).isBefore(moment(b[2]));
      });
    }
|}
];

let filterRepos: (int, array(RepoData.repo)) => array(RepoData.repo) = [%bs.raw
  {|
  function(totalMonths, repos) {
    var moment = require('moment');
    return repos.filter(function(repo) {
      return moment(repo[2]).isAfter(moment().subtract(totalMonths, 'months'));
    });
  }
|}
];

let make = (_children) => {
  ...component,
  initialState: () => {repos: None, loadingRepos: true},
  reducer: (action, _state) =>
    switch action {
    | Loaded(loadedRepos) =>
      ReasonReact.Update({
        repos: Some(sortRepos(filterRepos(12, loadedRepos))),
        loadingRepos: false
      })
    },
  didMount: (self) => {
    RepoData.fetchRepos()
    |> Js.Promise.then_(
         (repoData) => {
           repoData |> self.reduce((repoData) => Loaded(repoData));
           Js.Promise.resolve()
         }
       )
    |> ignore;
    ReasonReact.NoUpdate
  },
  render: (self) => {
    let repos =
      switch self.state.repos {
      | Some(repos) =>
        ReasonReact.arrayToElement(
          Array.map(
            (repo: RepoData.repo) => <Repo key=repo.name repo />,
            repos
          )
        )
      | None =>
        ReasonReact.stringToElement(
          "Sorry, it seems I've been extremely lazy as of late..."
        )
      };
    let loadingWrapper =
      self.state.loadingRepos ? ReasonReact.stringToElement("LOADING") : repos;
    <div> loadingWrapper </div>
  }
};
