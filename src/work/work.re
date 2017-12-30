let component = ReasonReact.statelessComponent("Work");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="work__container">
      <h2> (ReasonReact.stringToElement("About")) </h2>
      <p>
        (
          ReasonReact.stringToElement(
            "I'm currently working as a front-end dev at On Track Retail, developing JavaScript web apps for rail ticketing."
          )
        )
      </p>
    </div>
};
