[%bs.raw {|require('./mobileHeader.css')|}];

let component = ReasonReact.statelessComponent("MobileHeader");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="mobile-header">
      <div className="title-wrapper">
        <h1> (ReasonReact.stringToElement("Billy Reilly")) </h1>
      </div>
    </div>
};
