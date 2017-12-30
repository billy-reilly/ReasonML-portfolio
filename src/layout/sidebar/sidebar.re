[%bs.raw {|require('./sidebar.css')|}];

let component = ReasonReact.statelessComponent("Sidebar");

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="sidebar__container">
      <div className="sidebar__header">
        <h1>
          (ReasonReact.stringToElement("Billy"))
          <br />
          (ReasonReact.stringToElement("Reilly"))
        </h1>
        <hr />
      </div>
      <SidebarLinks />
    </div>
};
