let component = ReasonReact.statelessComponent("SidebarLink");

let make = (~link: SocialData.link, _children) => {
  ...component,
  render: (_self) =>
    <a className="sidebar_link" target="_blank" href=link.url>
      (ReasonReact.stringToElement(link.name))
    </a>
};
