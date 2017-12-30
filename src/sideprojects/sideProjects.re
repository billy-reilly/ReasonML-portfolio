let component = ReasonReact.statelessComponent("SideProjects");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div>
      <h2> (ReasonReact.stringToElement("Side Projects")) </h2>
      <p>
        (
          ReasonReact.stringToElement(
            "Here are some projects that I've recently been working on in my spare time:"
          )
        )
      </p>
      <Repositories />
    </div>
};
