[%bs.raw {|require('./repo.css')|}];

type state = {
  loadingTopics: bool,
  topics: TopicData.topics
};

type action =
  | TopicsLoaded(TopicData.topics);

let component = ReasonReact.reducerComponent("Repo");

let jsMoment: string => string = [%bs.raw
  {|
    function (updatedString) {
      var moment = require('moment');
      var updatedMoment = moment(updatedString).format("dddd, MMMM Do YYYY");
      return updatedMoment;
    }
|}
];

let emptyTopics: TopicData.topics = {names: [||]};

let make = (~repo: RepoData.repo, _children) => {
  ...component,
  initialState: () => {topics: emptyTopics, loadingTopics: true},
  reducer: (action, _state) =>
    switch action {
    | TopicsLoaded(loadedTopics) =>
      ReasonReact.Update({topics: loadedTopics, loadingTopics: false})
    },
  didMount: (self) => {
    TopicData.fetchTopics(repo.name)
    |> Js.Promise.then_(
         (topics) => {
           topics |> self.reduce((topics) => TopicsLoaded(topics));
           Js.Promise.resolve()
         }
       )
    |> ignore;
    ReasonReact.NoUpdate
  },
  render: (self) => {
    let topics =
      Array.length(self.state.topics.names) > 0 ?
        <div className="repo-footer">
          (
            ReasonReact.arrayToElement(
              Array.map(
                (topic: string) =>
                  <div className="topic" key=topic>
                    (ReasonReact.stringToElement(topic))
                  </div>,
                self.state.topics.names
              )
            )
          )
        </div> :
        ReasonReact.nullElement;
    <div className="repo__wrapper">
      <div className="repo-heading">
        <h3>
          <a target="_blank" href=repo.html_url>
            (ReasonReact.stringToElement(repo.name ++ "   "))
          </a>
          <small className="date-edited">
            (
              ReasonReact.stringToElement(
                "Last edited: " ++ jsMoment(repo.updated_at)
              )
            )
          </small>
        </h3>
      </div>
      <div className="repo-body">
        <p> (ReasonReact.stringToElement(repo.description)) </p>
      </div>
      topics
    </div>
  }
};
