[%bs.raw {|require('./responsiveRender.css')|}];

type state = {showSidebar: bool};

type action =
  | Resized(Dom.event);

let component = ReasonReact.reducerComponent("ResponsiveRender");

[@bs.val] external window : Dom.window = "window";

let make = (_children) => {
  ...component,
  initialState: () => {showSidebar: Webapi.Dom.Window.innerWidth(window) > 750},
  reducer: (action, _state) =>
    switch action {
    | Resized((e: Dom.event)) =>
      /* TODO: use e.target instead of window */
      ReasonReact.Update({
        showSidebar: Webapi.Dom.Window.innerWidth(window) > 750
      })
    },
  didMount: (self) => {
    Webapi.Dom.Window.addEventListener(
      "resize",
      self.reduce((e) => Resized(e)),
      Webapi.Dom.window
    );
    ReasonReact.NoUpdate
  },
  render: (self) =>
    self.state.showSidebar ?
      <div className="container-with-sidebar container-fluid">
        <Sidebar />
        <div className="content-beside-sidebar">
          <Work />
          <SideProjects />
        </div>
      </div> :
      <div className="container-without-sidebar container-fluid">
        <MobileHeader />
        <div className="content-no-sidebar">
          <Work />
          <SideProjects />
          <MobileFooter />
        </div>
      </div>
};
