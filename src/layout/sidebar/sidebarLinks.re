[%bs.raw {|require('./sidebarLinks.css')|}];

let component = ReasonReact.statelessComponent("SidebarLinks");

open SocialData;

let make = (_children) => {
  ...component,
  render: (_self) =>
    <div className="sidebar-links__wrapper">
      <SidebarLink link=githubLink />
      <SidebarLink link=stackOverflowLink />
      <SidebarLink link=linkedInLink />
    </div>
};
